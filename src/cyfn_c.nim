{.passL: "-lgc".}

when defined(windows):
    const ffiLib = "cyfncore.dll"
elif defined(macosx):
    const ffiLib = "libcyfncore.dylib"
else:
    const ffiLib = "libcyfncore.so"

proc cyfn_init*() {.importc, dynlib: ffiLib.}
proc cyfn_cleanup*() {.importc, dynlib: ffiLib.}
proc cyfn_scrape*(html: cstring, xpath: cstring): cstring {.importc, dynlib: ffiLib.}
