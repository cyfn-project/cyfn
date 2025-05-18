#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gc.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

void cyfn_init_gc()
{
    GC_INIT();
}

const char *cyfn_scrape(const char *html, const char *xpath_expr)
{
    htmlDocPtr doc = htmlReadMemory(html, strlen(html), NULL, NULL, HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
    if (!doc)
        return "Error: parse failed";

    xmlXPathContextPtr ctx = xmlXPathNewContext(doc);
    if (!ctx)
    {
        xmlFreeDoc(doc);
        return "Error: ctx failed";
    }

    xmlXPathObjectPtr result = xmlXPathEvalExpression((xmlChar *)xpath_expr, ctx);
    if (!result)
    {
        xmlXPathFreeContext(ctx);
        xmlFreeDoc(doc);
        return "Error: xpath failed";
    }

    xmlNodeSetPtr nodes = result->nodesetval;
    int len = (nodes) ? nodes->nodeNr : 0;

    char *output = GC_MALLOC(8192);
    output[0] = 0;

    for (int i = 0; i < len; i++)
    {
        xmlChar *content = xmlNodeGetContent(nodes->nodeTab[i]);
        if (content)
        {
            strncat(output, (char *)content, 8192 - strlen(output) - 2);
            strncat(output, "\n", 8192 - strlen(output) - 1);
            xmlFree(content);
        }
    }

    xmlXPathFreeObject(result);
    xmlXPathFreeContext(ctx);
    xmlFreeDoc(doc);

    return output;
}