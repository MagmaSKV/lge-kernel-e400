# Kernel LG E400 - SD-only Build

## Estado del Kernel
- ✅ Kernel base: 2.6.38-perf (LineageOS)
- ✅ Commit `5f6f855bbeb`: microSD-only boot guard
- ✅ Commit `9cbb27406e7`: eMMC controller disabled
- ✅ **Nuevo commit**: `e0eu-sd-only_defconfig` con SDC3 deshabilitado
- ✅ Configuración: `e0eu-sd-only_defconfig` (SD y WiFi solo)

## Configuración de Particiones SD
- **SDC1** (mmcblk0p1): SYSTEM (label: SYSTEM)
- **SDC2** (mmcblk0p2): DATA (label: DATA)  
- **SDC3** (mmcblk0p3): SDCARD (label: SDCARD)
- ✅ eMMC (SDC3) deshabilitado - no se usará

## Compilación Local

### Requisitos
```bash
apt-get update
apt-get install -y gcc-arm-linux-gnueabi binutils-arm-linux-gnueabi
```

### Compilar con nuevo defconfig
```bash
cd /tmp/e400-build/lgOpencode/lge-kernel-e400
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- e0eu-sd-only_defconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j4 zImage
```

### Resultado
- `arch/arm/boot/zImage`: Kernel compilado
- `arch/arm/boot/dts/e400.dtb`: Device tree

## Compilación en Github Actions

### Subir a GitHub
```bash
cd /tmp/e400-build/lgOpencode/lge-kernel-e400
git remote add origin <TU_REPO_URL>
git push -u origin android-msm-2.6.38
```

### Workflow de Github Actions
El workflow está en `.github/workflows/build-e400.yml`

Verificación automática del kernel compilado:
- ✅ SDC1 y SDC2 habilitados
- ✅ SDC3 deshabilitado
- ✅ Factory mode deshabilitado
- ✅ eMMC direct access deshabilitado

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

## Verificar Montaje por Labels

En el dispositivo LG E400:
```bash
mount | grep -E 'DATA|SYSTEM|SDCARD'
# Debe mostrar:
# /dev/block/mmcblk0p1 /data ext4 ro
# /dev/block/mmcblk0p2 /system ext4 ro  
# /dev/block/mmcblk0p3 /sdcard ext4 ro
```

## Notas
- El kernel verifica que el boot sea desde microSD (no eMMC)
- El controlador eMMC está deshabilitado
- Usa recovery CWM como base para pruebas
- Sistema de archivos montado por labels (DATA, SYSTEM, SDCARD)
