
/*
 *   Based on 
 *      code by Francesco Giacomini <francesco.giacomini@cnaf.infn.it>
 *        https://forum.nginx.org/read.php?29,283413,283421#msg-283421
 *      other modules from nginx
 *      With code updates by Brandon White <bjwhite@fnal.gov>
 *    */

#include <ngx_core.h>
#include <ngx_config.h>
#include <ngx_http_ssl_module.h>
#include <ngx_event_openssl.h>

static ngx_int_t ngx_ssl_allow_proxy_certs(ngx_ssl_t* ssl);
static char* ngx_gridproxy_merge_srv_conf(ngx_conf_t* cf, void*, void*);

static ngx_http_module_t  ctx = {
    NULL,          /* preconfiguration */
    NULL,          /* postconfiguration */
    NULL,          /* create main configuration */
    NULL,          /* init main configuration */
    NULL,          /* create server configuration */
    ngx_gridproxy_merge_srv_conf,    /* merge server configuration */
    NULL,          /* create location configuration*/
    NULL           /* merge location configuration*/
};

ngx_module_t  ngx_gridproxy_module = {
    NGX_MODULE_V1,
    &ctx,              /* module context */
    NULL,              /* module directives */
    NGX_HTTP_MODULE,   /* module type */
    NULL,              /* init master */
    NULL,              /* init module */
    NULL,              /* init process */
    NULL,              /* init thread */
    NULL,              /* exit thread */
    NULL,              /* exit process */
    NULL,              /* exit master */
    NGX_MODULE_V1_PADDING
};

static ngx_int_t ngx_ssl_allow_proxy_certs(ngx_ssl_t* ssl)
{

    X509_STORE *store = SSL_CTX_get_cert_store(ssl->ctx);
    if (store == NULL) {
        ngx_ssl_error(NGX_LOG_EMERG,
            ssl->log,
            0,
            "SSL_CTX_get_cert_store() failed");
        return NGX_ERROR;
    }
    X509_STORE_set_flags(store, X509_V_FLAG_ALLOW_PROXY_CERTS);
    return NGX_OK;

}

static char* ngx_gridproxy_merge_srv_conf(ngx_conf_t* cf, void* p1, void*p2)
{
    ngx_http_ssl_srv_conf_t *conf = ngx_http_conf_get_module_srv_conf(cf, ngx_http_ssl_module);

    /* avoid unused */
    int delta = (char *)p2 - (char*)p1;
    delta = delta * 2;

    if (conf->ssl.ctx != NULL) {
      if (ngx_ssl_allow_proxy_certs(&conf->ssl) != NGX_OK) {
        return NGX_CONF_ERROR;
      }
    }
    return NGX_CONF_OK;
}
