# `cyfn`

`cyfn` is a low-level, high-power scraping engine built in Nim, backed by C, and designed to be embedded, scripted, and deployed like a digital scalpel.

---

## Core Principles

* **C-first.** The heart of `cyfn` is written in pure C using `libxml2`, `libxslt`, and `boehm-gc`. It builds cleanly, links anywhere, and runs everywhere.
* **Nim-powered CLI.** Use Nim as a control layer: light, fast, embeddable, expressive.
* **Lua scripting (coming soon).** Drop into a REPL, run Lua scripts, call native C scrape functions — all without leaving the terminal.
* **Designed to embed.** The plan is to allow 'scriptability' through Python, Lua, Scheme - anything that speaks `cdecl`.

---

## Why?

Because scraping should be:

* **Fast**
* **Scriptable**
* **Portable**
* **Yours**

---

## Use Cases

* Extract titles, links, content from arbitrary HTML using XPath
* Repeatable scraping jobs from the CLI
* Metasploit-based template sharing

---

## Initial CLI example

At the moment the functionality is very basic:

```bash
cyfn --url=https://beyond-tabs.com --xpath=//h1
```

Result:

```
Find Your Next Tech Job
```

---

## Vision

* Clean C ABI
* Nim CLI wrapper
* Boehm GC-based memory management (no free() hell)
* Lua 5.4 embedded scripting (`cyfn.lua`)
* Python embedded scripting (`cyfn.py`)
* Chibi-Scheme integration (`cyfn.scm`)
* JSON output support
* REPL shell: `cyfn --shell`
* Headless scraping agent mode (daemon + socket API)
* WASM core build for browser/hybrid execution

