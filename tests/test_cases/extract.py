import re

markdown_file_path = 'markdown.md'
txt_file_path = 'grep_output.txt'
output_file_path = 'matching_results.txt'

# Read Markdown
with open(markdown_file_path, 'r', encoding='utf-8') as markdown_file:
    markdown_content = markdown_file.readlines()

# Read txt
with open(txt_file_path, 'r', encoding='utf-8') as txt_file:
    txt_content = txt_file.readlines()

def extract_info(line):
    pattern = r'\|([^|]+)\|([^|]+)\|([^|]+)\|([^|]+)\|'
    match = re.match(pattern, line)
    if match:
        file_path = match.group(1).strip()
        ranges = [item.strip() for item in match.group(4).split(',')]
        return (file_path,) + tuple(ranges)
    else:
        return None
        
# Extract Markdown
markdown_entries = []
for line in markdown_content:
    markdown = extract_info(line)
    # print(markdown)
    if markdown:
        markdown_entries.append(markdown)
        # print(path)

# print(markdown_entries)

# Extract txt
txt_entries = []
for line in txt_content:
    src_index = line.find("src/")
    path = line[src_index:line.find(":", src_index)].strip()
    match = re.search(r':(.+?):(\d+-\d+)', line)
    if match:
        syscall_name = match.group(1).strip()
        line_numbers = match.group(2).strip()
        txt_entries.append((path, syscall_name, line_numbers))
        # print(path)

# print(txt_entries)

# Compare
with open(output_file_path, 'w', encoding='utf-8') as output_file:
    for md_entry in markdown_entries:
        md_path = md_entry[0]
        md_values = md_entry[1:]
        for txt_entry in txt_entries:
            txt_path = txt_entry[0]
            txt_value = txt_entry[2]
            if md_path == txt_path:
                if txt_value in md_values:
                    output_file.write(f'{md_path}: {txt_entry}\n')

            

