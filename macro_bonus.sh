#!/bin/bash

# This script will insert # define BONUS 1
# at line 12 (just after header).
# for some IDE, definitions ar key to give you context
# help, even visual helpers that make our life easier.

macro="# define BONUS 1"

insert_macro() {
    local file="$1"
    if grep -qF "$macro" "$file"; then
        return
    fi
    sed -i '' "12i\\
$macro" "$file"
}

delete_macro() {
    local file="$1"
    sed -i '' "s/^$macro$//" "$file"
}

case "$1" in
    bonus)
        find . -type d -name "mlx" -prune -o -type f -name "*.h" -print | while read -r file; do
            insert_macro "$file"
        done
        ;;
    mandatory)
        find . -type d -name "mlx" -prune -o -type f -name "*.h" -print | while read -r file; do
            delete_macro "$file"
        done
        ;;
    *)
        echo "Use: $0 {bonus|mandatory}"
        exit 1
        ;;
esac
