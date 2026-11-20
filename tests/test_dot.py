"""Kiem tra cac ban tich vo huong cho cung ket qua voi ban tuan tu.

Cach chay (sau khi build):  python tests/test_dot.py
Gia tri khoi tao la boi cua 0.5 va 0.25 nen ket qua phai trung khop
chinh xac, khong phu thuoc thu tu cong.
"""
import os
import re
import subprocess
import sys

BIN = os.path.join(os.path.dirname(__file__), "..", "bin")
EXE = ".exe" if os.name == "nt" else ""


def run(prog, *args):
    """Chay mot chuong trinh trong bin/, tra ve gia tri 'ket qua'."""
    path = os.path.join(BIN, prog + EXE)
    out = subprocess.run([path, *map(str, args)], capture_output=True,
                         text=True, check=True).stdout
    return float(re.search(r"ket qua = (\S+)", out).group(1))


def main():
    loi = 0
    # n le, n khong chia het so luong, n nho hon so luong
    for n in [1, 3, 1000, 1001, 999983, 10_000_000]:
        ref = run("dot_seq", n)
        for p in [1, 2, 3, 4, 8]:
            got = run("dot_omp", n, p)
            ok = got == ref
            loi += not ok
            print(f"{'OK ' if ok else 'SAI'} dot_omp n={n:<9} p={p}: "
                  f"{got} (seq {ref})")
    print("Tat ca dung" if loi == 0 else f"{loi} truong hop sai")
    return 1 if loi else 0


if __name__ == "__main__":
    sys.exit(main())
