#ifndef CYFN_CORE_H
#define CYFN_CORE_H

#include <gc.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#ifdef __cplusplus
extern "C"
{
#endif

    void cyfn_init();

    void cyfn_cleanup();

    const char *cyfn_scrape(const char *html, const char *xpath_expr);

#ifdef __cplusplus
}
#endif

#endif