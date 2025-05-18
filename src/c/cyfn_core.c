#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gc.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

void cyfn_init()
{
    GC_INIT();
    xmlInitParser();
}

void cyfn_cleanup()
{
    xmlCleanupParser();
    // No GC cleanup needed as Boehm GC handles this automatically
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

    size_t buffer_size = 8192;
    size_t used_size = 0;
    char *output = GC_MALLOC(buffer_size);

    if (!output)
    {
        xmlXPathFreeObject(result);
        xmlXPathFreeContext(ctx);
        xmlFreeDoc(doc);
        return "Error: Memory allocation failed";
    }
    output[0] = 0;

    for (int i = 0; i < len; i++)
    {
        xmlChar *content = xmlNodeGetContent(nodes->nodeTab[i]);
        if (content)
        {
            size_t content_len = strlen((char *)content);
            size_t needed_size = used_size + content_len + 2; // +2 for newline and null terminator

            if (needed_size > buffer_size)
            {
                size_t new_size = buffer_size * 2;
                while (new_size < needed_size)
                    new_size *= 2;

                char *new_buffer = GC_MALLOC(new_size);
                if (!new_buffer)
                {
                    xmlFree(content);
                    continue; // Skip this node if allocation fails
                }

                memcpy(new_buffer, output, used_size + 1); // includes null terminator
                output = new_buffer;
                buffer_size = new_size;
            }

            memcpy(output + used_size, content, content_len);
            used_size += content_len;
            output[used_size] = '\n';
            used_size++;
            output[used_size] = '\0';
            xmlFree(content);
        }
    }

    xmlXPathFreeObject(result);
    xmlXPathFreeContext(ctx);
    xmlFreeDoc(doc);

    return output;
}