subdir('app1')
subdir('app2')

tut4 = alias_target(
	'tut4', tut4_app1_elf, tut4_app2_elf,
)

qemu_cmd = qemu_common + [
    '-device', 'loader,file=' + tut4_app1_elf.full_path(),
    '-device', 'loader,file=' + tut4_app2_elf.full_path(),
]

run_target(
	'tut4-qemu',
	command: qemu_cmd,
    depends : [s3k_elf, tut4_app1_elf, tut4_app2_elf],
)

run_target(
    'tut4-qemu-dbg',
    command: qemu_cmd + qemu_dbg_opts,
    depends : [s3k_elf, tut4_app1_elf, tut4_app2_elf],
)
