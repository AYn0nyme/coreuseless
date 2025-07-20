# 🏗️ Building & Installing coreuseless

This project uses **Meson** and **Ninja** for building.

---

## 📦 Requirements

- Meson
- Ninja
- A C compiler (e.g. `gcc` or `clang`)

---

## ⚙️ Build

```bash
meson setup build
meson compile -C build
```

---

## 📥 Install

Install to default prefix (`/usr/local`):

```bash
sudo meson install -C build
```

Custom install prefix (e.g. to `~/.local`):

```bash
meson setup build --prefix=$HOME/.local
meson install -C build
```

---

## 🧹 Clean

```bash
rm -rf build/
```

