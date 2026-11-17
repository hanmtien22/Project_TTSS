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
