subdir('app1')

tut1 = alias_target(
	'tut1', tut1_app1_elf     
)

qemu_cmd = qemu_common + [
    '-device', 'loader,file=' + tut1_app1_elf.full_path(),
]

run_target(
	'tut1-qemu',
	command: qemu_cmd,
    depends : [s3k_elf, tut1_app1_elf],
)

run_target(
    'tut1-qemu-dbg',
    command: qemu_cmd + qemu_dbg_opts,
    depends : [s3k_elf, tut1_app1_elf],
)
