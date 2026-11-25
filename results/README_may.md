# Cau hinh may do (Ming)

- CPU: 13th Gen Intel Core i9-13900H
- 14 nhan (6 nhan P + 8 nhan E), 20 luong
- Base speed: 2.60 GHz
- Cache: L1 1.2 MB, L2 11.5 MB, L3 24 MB (tong)
- RAM: 16 GB
- He dieu hanh: Windows 11
- Trinh bien dich: g++ 16.2.0 (MSYS2 UCRT64)

# Cach do baseline_naive.csv (21/11/2026)

- Cam sac, che do dien Best performance, dong ung dung khac
- Ghim vao CPU 0 (nhan P): (Get-Process -Id $PID).ProcessorAffinity = 1
- Moi cau hinh chay 5 lan, bo 1 lan chay nong may
- O2: g++ -O2
- O2_novec: g++ -O2 -fno-tree-vectorize