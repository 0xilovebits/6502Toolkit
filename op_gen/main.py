from bs4 import BeautifulSoup
import re

ADDR_MODE_MAP = {
    "Implied": "ADDR_IMPLIED",
    "Accumulator": "ADDR_ACCUMULATOR",
    "Immediate": "ADDR_IMMEDIATE",
    "Zero Page": "ADDR_ZEROPAGE",
    "Zero Page,X": "ADDR_ZEROPAGE_X",
    "Zero Page,Y": "ADDR_ZEROPAGE_Y",
    "Relative": "ADDR_RELATIVE",
    "Absolute": "ADDR_ABSOLUTE",
    "Absolute,X": "ADDR_ABSOLUTE_X",
    "Absolute,Y": "ADDR_ABSOLUTE_Y",
    "Indirect": "ADDR_INDIRECT",
    "Indirect,X": "ADDR_INDIRECT_X",
    "Indirect,Y": "ADDR_INDIRECT_Y",
    "Indexed Indirect (X)": "ADDR_INDIRECT_X",
    "Indirect Indexed (Y)": "ADDR_INDIRECT_Y",
}

C_HEADER = "Instruction opcode_table[256] = {\n"
C_FOOTER = "};"


def parse_cycles(cycles_str: str):
    """Extract base cycle count + keep extra text as comment"""
    match = re.search(r"\d+", cycles_str)
    base = int(match.group()) if match else 0
    extra = cycles_str[match.end() :].strip() if match else ""
    return base, extra


def scrape_6502_reference():
    resp = open("index.c", "r", encoding="utf-8").read()
    soup = BeautifulSoup(resp, "html.parser")
    instructions = {}

    for h3 in soup.find_all("h3"):
        if not h3.a or not h3.a.get("name"):
            continue

        mnemonic = h3.a["name"]
        desc_tag = h3.find_next("p")

        flags_table = desc_tag.find_next("table")
        addr_table = flags_table.find_next("table") if flags_table else None
        addr_modes = []

        if addr_table:
            for row in addr_table.find_all("tr")[1:]:
                cols = [c.get_text(" ", strip=True) for c in row.find_all("td")]
                if len(cols) >= 4:
                    opcode_str = cols[1].replace("$", "").strip()
                    try:
                        opcode = int(opcode_str, 16)
                    except ValueError:
                        continue
                    addr_modes.append(
                        {
                            "mode": cols[0],
                            "opcode": opcode,
                            "bytes": int(cols[2]),
                            "cycles": cols[3],
                        }
                    )

        if addr_modes:
            instructions[mnemonic] = addr_modes

    return instructions


if __name__ == "__main__":
    data = scrape_6502_reference()

    table = []

    for mnemonic, modes in data.items():
        for m in modes:
            if m["mode"] not in ADDR_MODE_MAP:
                continue
            mode_enum = ADDR_MODE_MAP[m["mode"]]
            base_cycles, extra = parse_cycles(m["cycles"])
            entry = f'    [0x{m["opcode"]:02X}] = OPCODE("{mnemonic}", {mode_enum}, {m["bytes"]}, {base_cycles}),'
            if extra:
                entry += f" // {extra}"
            table.append(entry)

    print(C_HEADER)
    print("\n".join(table))
    print(C_FOOTER)
