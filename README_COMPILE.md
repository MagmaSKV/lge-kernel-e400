# Kernel LG E400 - Instrucciones de Compilación

## Estado del Kernel
- ✅ Kernel base: 2.6.38-perf (LineageOS)
- ✅ Commit `5f6f855bbeb`: microSD-only boot guard
- ✅ Commit `9cbb27406e7`: eMMC controller disabled
- ✅ Configuración: `e0eu-no-emmc_defconfig`
- ✅ Kernel extraído del boot.img original

## Compilación Local

### Requisitos
```bash
apt-get update
apt-get install -y gcc-arm-linux-gnueabi binutils-arm-linux-gnueabi
```

### Compilar
```bash
cd /tmp/e400-build/lgOpencode/lge-kernel-e400
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- e0eu-no-emmc_defconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j4
```

### Resultado
- `arch/arm/boot/zImage`: Kernel compilado
- `arch/arm/boot/dts/e400.dtb`: Device tree (si existe)

## Compilación en Github Actions

### Subir a GitHub
```bash
cd /tmp/e400-build/lgOpencode/lge-kernel-e400
git remote add origin <TU_REPO_URL>
git push -u origin android-msm-2.6.38
```

### Workflow de Github Actions
El workflow ya está en `.github/workflows/build-e400.yml`

## Extraer Kernel y Ramdisk del boot.img Original

```bash
mkdir -p unpacked_boot
cd unpacked_boot
unpackbootimg -i ../boot.img -o .

mv boot.img-kernel ../extracted_kernel.img
mv boot.img-ramdisk ../extracted_ramdisk.img
```

## Crear Nuevo boot.img con mkbootimg

```bash
mkdir -p bootparts
cd bootparts
mkbootimg --kernel ../extracted_kernel.img \
          --ramdisk ../extracted_ramdisk.img \
          --cmdline "androidboot.hardware=e0" \
          --base 0x0 \
          --pagesize 4096 \
          --output ../new_boot.img

cd ..
```

## Probar con fastboot

```bash
fastboot boot new_boot.img
```

## Estructura de particiones
- `/dev/block/mmcblk0p1`: system (UUID: 57f8f4bc-abf4-0000-675f-946fc0f9f25b)
- `/dev/block/mmcblk0p2`: DATA (UUID: 711d2f54-8128-4155-9e9b-6b02e25c2a5f)

## Notas
- El kernel verifica que el boot sea desde microSD (no eMMC)
- El controlador eMMC está deshabilitado
- Usa recovery CWM como base para pruebas
