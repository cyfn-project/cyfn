import parseopt, httpClient, strutils, cyfn_c

proc showHelp() =
  echo """
  Usage:
    cyfn --url <URL> --xpath <XPATH>

  Options:
    --url <URL>       Target page to scrape
    --xpath <XPATH>   XPath expression
    --help            This help message
  """

when isMainModule:
  cyfn_init()

  var
    url = ""
    xpath = ""

  for kind, key, val in getopt():
    case kind
    of cmdLongOption:
      case key
      of "url": url = val
      of "xpath": xpath = val
      of "help": showHelp(); quit(0)
      else: discard
    else: discard

  if url.len == 0 or xpath.len == 0:
    showHelp()
    quit(1)

  try:
    let html = newHttpClient().getContent(url)
    let result = $cyfn_scrape(html.cstring(), xpath.cstring())

    if result.len == 0:
      stderr.writeLine("cyfn_scrape returned nothing.")
      quit(2)

    if result.startsWith("Error:"):
      stderr.writeLine("Scraper error: " & result)
      quit(2)

    echo result
  except HttpRequestError as e:
    stderr.writeLine("HTTP error: " & e.msg)
    quit(3)
  except CatchableError as e:
    stderr.writeLine("Unexpected error: " & e.msg)
    quit(99)

