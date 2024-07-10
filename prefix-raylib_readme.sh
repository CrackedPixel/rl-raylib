#!/bin/bash

readme="README.md"

insert_text=$(<"prefix-raylib_readme.md")

existing_text=$(<"$readme")

combined_text="$insert_text"$'\n'"$existing_text"

echo "$combined_text" > "$readme"
