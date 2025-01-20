# Sitemap Generator

This C++ program generates an XML sitemap from a list of URLs provided in an input text file. It reads the URLs line-by-line from the input file and writes the sitemap in the proper XML format to an output file.

## Features
- Reads URLs from a plain text file.
- Generates a valid XML sitemap.
- Error handling for file operations.

---

## Requirements
- C++17 or later.
- A compiler such as Clang or GCC.

---

## How to Build and Run the Program

### Using Clang
1. **Compile the program:**
   ```bash
   clang++ -std=c++17 -o sitemap_generator sitemap_generator.cpp
   ```

2. **Run the program:**
   ```bash
   ./sitemap_generator <input_file> <output_file>
   ```
   Replace `<input_file>` with the path to your text file containing URLs and `<output_file>` with the desired output file name.

### Using GCC
1. **Compile the program:**
   ```bash
   g++ -std=c++17 -o sitemap_generator sitemap_generator.cpp
   ```

2. **Run the program:**
   ```bash
   ./sitemap_generator <input_file> <output_file>
   ```
   Replace `<input_file>` with the path to your text file containing URLs and `<output_file>` with the desired output file name.

---

## Input File Format
The input file should contain one URL per line. Example:
```
https://example.com/page1
https://example.com/page2
https://example.com/page3
```

---

## Output File Format
The output file will be in XML sitemap format. Example:
```xml
<?xml version="1.0" encoding="UTF-8"?>
<urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">
  <url>
    <loc>https://example.com/page1</loc>
  </url>
  <url>
    <loc>https://example.com/page2</loc>
  </url>
  <url>
    <loc>https://example.com/page3</loc>
  </url>
</urlset>
```

---

## Error Handling
- If the input file cannot be opened, the program will print an error message and exit.
- If no URLs are found in the input file, the program will print an error message and exit.
- If the output file cannot be opened, the program will print an error message and exit.

---

## License
This project is licensed under the MIT License.

---

## Contribution
Feel free to submit issues or contribute to this project by creating pull requests on GitHub.

