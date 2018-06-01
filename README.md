# OpenICP-BR
*Read this in other languages: [English](README.md), [Português (Brasil)](README.pt-BR.md).*

<h1 align="center">
  <br>
  <img src="https://github.com/gjvnq/OpenICP-BR/blob/master/res/logo-512.png" alt="OpenICP-BR logo" width="160">
</h1>

<h4 align="center">An opensource GUI tool for digital sigatures that are legally valid in Brazil (standard: <a href="http://www.iti.gov.br/icp-brasil" target="_blank">ICP-Brasil</a>).</h4>

OpenICP-BR is a cross-platform (Linux, macOS, Windows) desktop app for signing documents as well as verifying the sigunatures acording to the <a href="http://www.iti.gov.br/icp-brasil" target="_blank">ICP-Brasil</a> (Brazilian Publick Key Infrastructure).

## Install

[See all released versions](https://github.com/gjvnq/OpenICP-BR/releases).

### OS X

1. Download the file [OpenICP-BR-v0.2.1.dmg](https://github.com/gjvnq/OpenICP-BR/releases/download/v0.1.0/OpenICP-BR-v0.2.1.dmg).
2. Open it and drag the app to the folder `Applications`.
3. Done!

### Windows

1. Download the file [Instalador-OpenICP-BR-v0.2.1-i686.exe](https://github.com/gjvnq/OpenICP-BR/releases/download/v0.2.1/Instalador-OpenICP-BR-v0.2.1-i686.exe).
2. Run it.
3. Follow the installer instructions.
4. Done!

OBS: You don't need administrator privileges to install the Windows version, because it does *not* install to `C:\Program Files (x86)`, but rather to `C:\Users\My User\AppData\Local`.

### Linux

*Arch Linux:*

1. Install via AUR: `pacaur -S openicp-br`.

OR

1. Download the file [openicp-br-0.2.1-1-x86_64.pkg.tar.xz](https://github.com/gjvnq/OpenICP-BR/releases/download/v0.2.1/openicp-br-0.2.1-1-x86_64.pkg.tar.xz).
2. Install it: `sudo pacman -U openicp-br-0.2.1-1-x86_64.pkg.tar.xz`.

*Outras distribuições Linux:*

1. Download the file [OpenICP-BR-v0.2.1-x86_64.tar.gz](https://github.com/gjvnq/OpenICP-BR/releases/download/v0.2.1/OpenICP-BR-v0.2.1-x86_64.tar.gz).
2. Make sure you have [wxWidgets](https://wxwidgets.org) installed.
3. Extract it on the root directory: `sudo tar xvf OpenICP-BR-v0.2.1-x86_64.tar.gz -C /`.

## Compilation (for developers)

Follow these instructions:

  * [Linux 64bit](COMPILE.linux.arch.64bit.md)
  * [macOS](COMPILE.macOS.md)
  * [Windows](COMPILE.win.md)

## Features

- [x] Add certificates
- [x] Sign documents
- [ ] Verify signatures
- [ ] Check CRL (Certificate Revocation List)
- [ ] Support certificates in smart cards
- [ ] Auto updates

## Built with
- [wxWidgets](https://wxwidgets.org)
- [OpenSSL](https://www.openssl.org)

## License

[AGPL - Affero GNU Public License](https://www.gnu.org/licenses/agpl-3.0.en.html)