# Quy uoc lam viec chung

## Nhanh (branch)

- `main` luon build duoc, khong push thang len `main`.
- Moi nguoi lam tren nhanh rieng, tao tu `main`:
  - Long: `long_branch`
  - Manh, Ming: `feature/<ten>-<viec>`, vi du `feature/manh-cannon-padding`,
    `feature/ming-tiled-kernel`
- Truoc khi mo PR, cap nhat nhanh tu `main` moi nhat:

```
git fetch origin
git merge origin/main
```

## Commit

Message theo Conventional Commits, tieng Viet khong dau:

```
<loai>(<pham-vi>): <mo ta ngan>
```

| Loai       | Dung khi                                   |
| ---------- | ------------------------------------------ |
| `feat`     | them chuc nang moi                         |
| `fix`      | sua loi                                    |
| `perf`     | tang toc, khong doi ket qua                |
| `refactor` | sua cau truc code, khong doi hanh vi       |
| `test`     | them/sua test                              |
| `bench`    | so lieu do, script do                      |
| `docs`     | tai lieu, bao cao                          |
| `build`    | Makefile, build.bat, co bien dich          |
| `chore`    | viec vat khac (.gitignore, thu muc, tag)   |

Pham vi thuong dung: `dot`, `matmul`, `kernels`, `common`, `bench`, `report`, `ai`.

Vi du:

```
feat(dot): ban OpenMP voi reduction
fix(matmul): bo phan padding khi gather C
```

Nguyen tac:

- Moi commit chi chua mot thay doi co y nghia va phai build duoc.
- Commit nho, push trong ngay lam viec; khong don commit vao cuoi tuan.
- `git config user.email` phai trung email tai khoan GitHub, neu khong
  commit se khong duoc tinh vao dong gop.

## Pull Request va review

1. Keo issue sang cot *In progress* tren GitHub Projects.
2. Lam xong mot phan thi mo PR vao `main`, mo ta ghi `Closes #<so issue>`,
   kem ket qua test hoac so lieu do neu co.
3. Nguoi review theo vong:

   | Tac gia | Nguoi review |
   | ------- | ------------ |
   | Manh    | Long         |
   | Ming    | Manh         |
   | Long    | Ming         |

4. Gop y ngay tren PR (comment tren dong code), khong trao doi rieng ngoai
   Zalo de con dau vet.
5. Merge bang **Merge commit** de giu lich su commit tung ngay; chi dung
   *Squash and merge* khi PR co qua nhieu commit vun.
6. Khong tu sua code trong thu muc cua nguoi khac khi chua co PR. Muon doi
   `include/kernels.h` thi phai qua PR duoc ca 3 nguoi duyet.

## Cuoi tuan

Nguoi phu trach tuan (lan luot Long, Manh, Ming, Long) gan tag `v0.x`,
viet Release notes ngan va commit so lieu do moi vao `results/`.
