subdir('app1')
subdir('app2')

tut2 = alias_target(
	'tut2', tut2_app1_elf, tut2_app2_elf,
)

qemu_cmd = qemu_common + [
    '-device', 'loader,file=' + tut2_app1_elf.full_path(),
    '-device', 'loader,file=' + tut2_app2_elf.full_path(),
]

run_target(
	'tut2-qemu',
	command: qemu_cmd,
    depends : [s3k_elf, tut2_app1_elf, tut2_app2_elf],
)

run_target(
    'tut2-qemu-dbg',
    command: qemu_cmd + qemu_dbg_opts,
    depends : [s3k_elf, tut2_app1_elf, tut2_app2_elf],
)
