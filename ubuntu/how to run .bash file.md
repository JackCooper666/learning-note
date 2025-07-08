# 1. **Ensure it has execute permissions**

Open a terminal and run:

```bash
chmod +x your_script.bash
```
Replace `your_script.bash` with the actual filename.

# 2. **Run the script**

You have a few options:

- **With relative path (recommended):**
```bash
./your_script.bash
```
- **With full path:**
```bash
/path/to/your_script.bash
```
- **Using `bash` explicitly (no need to `chmod +x`):**
```bash
bash your_script.bash
```

### Notes:

- If you get `command not found` or `permission denied`, make sure you're in the right directory and have permission.
    
- Make sure the script starts with the correct **shebang**:
```bash
#!/bin/bash
```
    at the top of the file.
