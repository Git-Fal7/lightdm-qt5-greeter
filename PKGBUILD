pkgname=lightdm-qt5-greeter
pkgver=0.1
pkgrel=1
pkgdesc='lightdm-qt5-greeter is a simple frontend for the lightdm displaymanager, written in c++ and qt5.'
arch=('x86_64')
url="https://github.com/git-fal7/$pkgname"
license=('LGPL2.1')
depends=('qt5-base' 'liblightdm-qt5' 'lightdm')
makedepends=('cmake')

provides=("$pkgname")
conflicts=("$pkgname-git")

backup=("etc/lightdm/$pkgname.conf")
source=("$pkgname::git+$url.git")
sha512sums=('SKIP')

build() {
  cd "$pkgname"
  mkdir -p build
  cd build
  cmake ..
  make
}

package() {
  cd $pkgname
  cd build
  make DESTDIR="$pkgdir/" install
}
