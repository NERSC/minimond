/* printer_amqp.c */


#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minimond.h"


#ifdef AMQP
#include <amqp_tcp_socket.h>
#include <amqp.h>
#include <amqp_framing.h>


metric_group *amqp_printer(metric_group *mg, config *c) {
    char buf[MAX_LINE];
    int i = 0;
    metric m;
    int ret;


    amqp_socket_t *socket = NULL;
    amqp_connection_state_t conn;


    /* Create an AMQP socket and connect to the exchange */
    conn = amqp_new_connection();
    socket = amqp_tcp_socket_new(conn);
    if(!socket) {
        log_str(LOG_DEBUG,
                "Failed to create amqp socket: %s.  Metrics will not be sent during this collection period\n",
                strerror(errno));
        return mg;
    }

    ret = amqp_socket_open(socket, c->amqp_host, c->amqp_port);
    if(ret != AMQP_STATUS_OK) {
        log_str(LOG_DEBUG,
                "Failed to open amqp socket %s:%d: %d.  Metrics will not be sent during this collection period\n",
                c->amqp_host, c->amqp_port, ret);
        return mg;
    }

    /* Log in to the exchange. */
    amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "guest", "guest"),
                    "Logging in";
    amqp_channel_open(conn, 1);
    amqp_get_rpc_reply(conn), "Opening channel";


    for (i = 0; i < METRIC_GROUP_MAX_SIZE ; i++) {

        amqp_basic_properties_t props;
        props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
        props.content_type = amqp_cstring_bytes("text/plain");
        props.delivery_mode = 2; /* persistent delivery mode */

        m = mg->metrics[i];

        if(metric_is_new(&m)) {
            break;
        }


        switch(mg->type) {
            case VALUE_INT:
                snprintf(buf, MAX_LINE, "%.32s_%.32s_%d", mg->name, m.name, m.val.i);
                break;
            case VALUE_LONG:
                snprintf(buf, MAX_LINE, "%.32s_%.32s_%ld", mg->name, m.name, m.val.l);
                break;
            case VALUE_ULLONG:
                snprintf(buf, MAX_LINE, "%.32s_%.32s_%llu", mg->name, m.name, m.val.llu);
                break;
            case VALUE_FLOAT:
                snprintf(buf, MAX_LINE, "%.32s_%.32s_%f", mg->name, m.name, m.val.f);
                break;
            case VALUE_DOUBLE:
                snprintf(buf, MAX_LINE, "%.32s_%.32s_%lf", mg->name, m.name, m.val.d);
                break;
            default:
                fatal_error("Unsupported metric type: %d\n", mg->type);
                break;
        }

        if(amqp_basic_publish(conn,
                1,
                amqp_cstring_bytes(c->amqp_exchange),
                amqp_cstring_bytes(c->amqp_routingkey),
                0,
                0,
                &props,
                amqp_cstring_bytes(buf)) != AMQP_STATUS_OK ) {
            log_str(LOG_DEBUG,
                    "Failed to send on AMQP connection: %s.  Metrics will not be sent during this collection period\n",
                    strerror(errno));
        }
        else if(c->debug) {
            log_str(LOG_DEBUG,
                    "Sent %s on AMQP connection to %s:%d\n",
                    buf, c->amqp_host, c->amqp_port);
        }

    }

    amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS);
    amqp_connection_close(conn, AMQP_REPLY_SUCCESS);
    amqp_destroy_connection(conn);
    return mg;

}
#endif /* AMQP */
