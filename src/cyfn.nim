import parseopt, cyfn_c

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
  var
    url = ""
    xpath = ""
    result: cstring

  for kind, key, val in getopt():
    case key
    of "url": url = val
    of "xpath": xpath = val
    of "help": showHelp(); quit(0)
    else: discard

  if url.len == 0 or xpath.len == 0:
    showHelp()
    quit(1)

  result = cyfn_scrape(url.cstring(), xpath.cstring())
