subdir('app1')
subdir('app2')

tut5 = alias_target(
	'tut5', tut5_app1_elf, tut5_app2_elf,
)

qemu_cmd = qemu_common + [
    '-device', 'loader,file=' + tut5_app1_elf.full_path(),
    '-device', 'loader,file=' + tut5_app2_elf.full_path(),
]

run_target(
	'tut5-qemu',
	command: qemu_cmd,
    depends : [s3k_elf, tut5_app1_elf, tut5_app2_elf],
)

run_target(
    'tut5-qemu-dbg',
    command: qemu_cmd + qemu_dbg_opts,
    depends : [s3k_elf, tut5_app1_elf, tut5_app2_elf],
)
