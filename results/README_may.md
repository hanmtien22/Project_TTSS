# Cau hinh may do (Ming)

- CPU: 13th Gen Intel Core i9-13900H
- 14 nhan (6 nhan P + 8 nhan E), 20 luong
- Base speed: 2.60 GHz
- Cache: L1 1.2 MB, L2 11.5 MB, L3 24 MB (tong)
- RAM: 16 GB
- He dieu hanh: Windows 11
- Trinh bien dich: g++ 16.2.0 (MSYS2 UCRT64)

# Cach do baseline_naive.csv (21/11/2026)

- Cam sac, che do dien Balanced, dong ung dung khac
- Ghim vao CPU 0 (nhan P): (Get-Process -Id $PID).ProcessorAffinity = 1
- Moi cau hinh chay 5 lan, bo 1 lan chay nong may
- O2: g++ -O2
- O2_novec: g++ -O2 -fno-tree-vectorize

# Do kich ban 3 (28/11/2026)

- Cam sac, Power mode: Best Performance (Plugged in), dong ung dung khac
- Ghim CPU 0: (Get-Process -Id $PID).ProcessorAffinity = 1
- naive, tiled: g++ -O2
- simd, tiled_simd: g++ -O2 -mavx2 -mfma -ffp-contract=fast -fopenmp-simd
- Nhan trong CSV: O2_avx2fma_cho_simd

## Cac file
- kich_ban_3.csv: 4 kernel x n = 256, 512, 1024, 2048, tile = 64
  - Dong naive n=2048 reps=5 co do lech chuan khoang 10.7% nen do lai voi reps=7 (dong cuoi file), dung dong reps=7
- tile_sweep.csv: tiled va tiled_simd, tile = 16, 32, 64, 128, n = 1024 va 2048; 2 dong cuoi la tiled_simd n=2000 (kiem tra xung dot cache)
- tile_kiem_chung.csv: do lai tiled_simd n = 2000, 2048, tile = 64, 128 voi reps=7 (trong luc do tile_sweep co Java update chay ngam)

## Ghi chu
- So lieu baseline_naive.csv (21/11) do o che do Balanced, khong so sanh truc tiep voi so lieu 28/11
- Chon tile mac dinh = 64