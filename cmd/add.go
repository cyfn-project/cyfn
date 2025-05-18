package cmd

import (
	"fmt"
	"os"
	"path/filepath"
	"time"

	"github.com/spf13/cobra"
)

var targetURL string
var scriptLang string

var addCmd = &cobra.Command{
	Use:   "add [name]",
	Short: "Add a new target",
	Args:  cobra.ExactArgs(1),
	Run: func(cmd *cobra.Command, args []string) {
		name := args[0]

		targetPath := filepath.Join("targets", name+".yaml")
		scriptPath := filepath.Join("scripts", name+"."+extForLang(scriptLang))

		if _, err := os.Stat(targetPath); err == nil {
			fmt.Println("Target already exists:", targetPath)
			os.Exit(1)
		}

		targetContent := fmt.Sprintf(
			`name: %s
url: %s
created: %s
script: %s
`, name, targetURL, time.Now().Format(time.RFC3339), scriptPath)

		err := os.WriteFile(targetPath, []byte(targetContent), 0644)

		if err != nil {
			fmt.Println("Error writing target file:", err)
			os.Exit(1)
		}
		fmt.Printf("Created target file: %s\n", targetPath)

		if _, err := os.Stat(scriptPath); os.IsNotExist(err) {
			os.WriteFile(scriptPath, []byte(scriptStub(scriptLang)), 0755)

			fmt.Printf("Created script file: %s\n", scriptPath)
		}

		fmt.Printf("Target URL: %s\n", targetURL)
		fmt.Printf("Script language: %s\n", scriptLang)
		fmt.Printf("Script path: %s\n", scriptPath)

		fmt.Printf("Added target '%s' with script '%s'\n", name, scriptPath)
	},
}

func init() {
	addCmd.Flags().StringVarP(&targetURL, "url", "u", "", "Target base URL (required)")
	addCmd.MarkFlagRequired("url")

	addCmd.Flags().StringVarP(&scriptLang, "lang", "l", "sh", "Script language: sh, lua, go")
}

func extForLang(lang string) string {
	switch lang {
	case "lua":
		return "lua"
	case "go":
		return "go"
	default:
		return "sh"
	}
}

func scriptStub(lang string) string {
	switch lang {
	case "lua":
		return `-- Lua scraping stub
print("Hello from Lua script")`
	case "go":
		return `package main

import "fmt"

func main() {
	fmt.Println("Hello from Go script")
}`
	default:
		return "#!/bin/bash\necho 'Hello from shell script'"
	}
}
