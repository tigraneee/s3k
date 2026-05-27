platform_srcs = files(
    'ns16550a.c',
)

platform_linker_script = meson.current_source_dir() / 'qemu_virt.ld'

platform_dep = declare_dependency(
    sources: platform_srcs,
    link_args: [
        '-T', platform_linker_script,
    ],
)
