#!/bin/sh
file_path="bn"

# Check if the file exists
if [ -f "$file_path" ]; then
  build_number=$(cat "$file_path")
else
  build_number=1
fi
build_number=$((build_number + 1))


echo "$build_number" > "$file_path"
echo "New build number: $build_number"
