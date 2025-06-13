import std/httpclient, std/strutils, std/streams
import chame/minidom
import chame/tags


func escapeText(s: string, attribute_mode = false): string =
  result = ""
  var nbsp_mode = false
  var nbsp_prev = '\0'
  for c in s:
    if nbsp_mode:
      if c == char(0xA0):
        result &= "&nbsp;"
      else:
        result &= nbsp_prev & c
      nbsp_mode = false
    elif c == '&':
      result &= "&amp;"
    elif c == char(0xC2):
      nbsp_mode = true
      nbsp_prev = c
    elif attribute_mode and c == '"':
      result &= "&quot;"
    elif not attribute_mode and c == '<':
      result &= "&lt;"
    elif not attribute_mode and c == '>':
      result &= "&gt;"
    else:
      result &= c

func `$`*(node: Node): string =
  result = ""
  if node of Element:
    let element = Element(node)
    var x = ""
    if element.namespace == Namespace.SVG:
      x = "svg "
    elif element.namespace == Namespace.MATHML:
      x = "math "
    result = "<" & x & element.localNameStr
    for k, v in element.attrsStr:
      result &= ' ' & k & "=\"" & v.escapeText(true) & "\""
    result &= ">"
    for node in element.childList:
      result &= $node
    result &= "</" & x & element.localNameStr & ">"
  elif node of Text:
    let text = Text(node)
    result = text.data.escapeText()
  elif node of Comment:
    result = "<!-- " & Comment(node).data & "-->"
  elif node of DocumentType:
    result = "<!DOCTYPE" & ' ' & DocumentType(node).name & ">"
  elif node of Document:
    result = "Node of Document"


proc main() =
  echo "Nimcurse Recon Unit: DOM Extraction"
  
  let client = newHttpClient()
  let html = client.getContent("https://beyond-tabs.com")

  let document = parseHTML(newStringStream(html))
  var s = ""
  for x in document.childList:
    s &= $x & '\n'

  echo s.len

when isMainModule:
  main()
