with open('grep_out.txt', 'r') as file:
    lines = file.readlines()

output_lines = []

for i in range(len(lines) - 1):
    line = lines[i]
    next_line = lines[i + 1]

    # Extract syscall
    fn_index = line.find("fn ")
    syscall_name = line[fn_index + 3 : line.find("(", fn_index)].strip()

    # Get end number
    next_line_number = int(next_line.split(":")[1])

    # Construct output
    output_line = f"{line.split(':')[0]}:{syscall_name}:{line.split(':')[1]}-{next_line_number-1}\n"
    output_lines.append(output_line)

# Output
with open('grep_output.txt', 'w') as output_file:
    output_file.writelines(output_lines)
