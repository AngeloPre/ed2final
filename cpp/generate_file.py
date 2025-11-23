import os

TARGET_SIZE = 1 * 1024 * 1024 * 1024  # 1 GB in bytes
FILENAME = "lorem_1GB.txt"

lorem = (
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
    "Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. "
    "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi "
    "ut aliquip ex ea commodo consequat. Duis aute irure dolor in "
    "reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. "
    "Excepteur sint occaecat cupidatat non proident, sunt in culpa qui "
    "officia deserunt mollit anim id est laborum.\n"
)

# Pre-build a larger chunk to speed up writing
chunk = lorem * 1024  # adjust multiplier if you want different speed/memory tradeoff
chunk_bytes = chunk.encode("utf-8")
chunk_size = len(chunk_bytes)

written = 0

with open(FILENAME, "wb") as f:
    while written + chunk_size <= TARGET_SIZE:
        f.write(chunk_bytes)
        written += chunk_size

    # Write the remaining bytes if needed
    remaining = TARGET_SIZE - written
    if remaining > 0:
        f.write(chunk_bytes[:remaining])

print(f"Wrote {TARGET_SIZE} bytes to {FILENAME}")