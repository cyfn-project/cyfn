package cmd

import (
	"fmt"
	"os"

	"github.com/spf13/cobra"
)

var initCmd = &cobra.Command{
	Use:   "init",
	Short: "Initialize a new cyfn workspace",
	Run: func(cmd *cobra.Command, args []string) {
		dirs := []string{"targets", "scripts", "results", "logs"}
		for _, dir := range dirs {
			if err := os.MkdirAll(dir, 0755); err != nil {
				fmt.Printf("Error creating %s: %v\n", dir, err)
				os.Exit(1)
			}
		}
		f, err := os.Create("config.yaml")
		if err != nil {
			fmt.Println("Error creating config.yaml:", err)
			os.Exit(1)
		}
		defer f.Close()

		_, err = f.WriteString("# cyfn global config\n")

		if err != nil {
			fmt.Println("Error writing to config.yaml:", err)
			os.Exit(1)
		}

		fmt.Println("Workspace initialized.")
	},
}
