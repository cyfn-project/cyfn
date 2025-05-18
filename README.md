# `cyfn`

**cyfn** is a low-level, high-power scraping engine built in Nim, backed by C, and designed to be embedded, scripted, and deployed like a digital scalpel.

Think of it as _Metasploit for scraping_: extract data with surgical precision using XPath, a native C core, and a fast, zero-boilerplate CLI.

---

## Core Principles

- **C-first.**  
  The core is written in pure C using `libxml2`, `libxslt`, and `boehm-gc`. It builds cleanly, links anywhere, and runs everywhere.

- **[Nim](https://nim-lang.org/)-powered CLI.**  
  The CLI is built in Nim: light, expressive, portable, and _fast_.

- **Lua scripting (coming soon).**  
  Drop into a REPL, run Lua scripts, and call `cyfn_scrape()` natively.

- **Designed to embed.**  
  The goal is full `cdecl` exposure: Python, Lua, Scheme — whatever you speak, `cyfn` will listen.

---

## Why?

Because scraping should be:

- **Fast**
- **Scriptable**
- **Portable**

---

## Use Cases

- Extract headings, links, or fragments from raw HTML using XPath
- Run repeatable CLI scraping jobs
- Eventually: define and share “scraping payloads” like Metasploit modules

---

## CLI Example

Basic functionality right now:

```bash
cyfn --url=https://beyond-tabs.com --xpath=//h1
````

Result:

```
Find Your Next Tech Job
```

---

## Vision & Roadmap

* Clean C ABI (`const char* cyfn_scrape(const char*, const char*)`)
* Nim CLI wrapper
* Boehm GC-based memory management (no `free()` hell)
* Lua 5.4 embedded scripting (`cyfn.lua`)
* Python embedded scripting (`cyfn.py`)
* Chibi-Scheme integration (`cyfn.scm`)
* JSON output mode (`--json`)
* Interactive REPL shell (`cyfn --shell`)
* Daemon mode with socket API
* [XFrames](https://github.com/xframes-project/xframes)-powered GUI for interactive scraping (driven by Lua)
