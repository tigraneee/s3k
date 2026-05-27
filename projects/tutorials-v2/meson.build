project('tutorials', 'c', 
	version: '0.1', 
	meson_version: '>=1.1.0', 
	default_options: [
		'buildtype=debugoptimized',
		'c_std=gnu11',
	]
)

s3k = subproject('s3k')
libs3k_dep = s3k.get_variable('lib_dep')
s3k_elf = s3k.get_variable('elf')

subdir('platform')
subdir('common')

# Common compiler arguments for the apps
add_project_arguments(
    '-specs=picolibc.specs',
    language: 'c',
)

# Common linker arguments for the apps
add_project_link_arguments(
    '-nostartfiles',
    '-specs=picolibc.specs',
    language: 'c',
)

# All apps depend on libs3k
add_project_dependencies(
    libs3k_dep,
    language: 'c',
)

qemu_system_riscv64 = find_program('qemu-system-riscv64', required: false)

qemu_common = [
    qemu_system_riscv64,
    '-machine', 'virt',
    '-smp', '2',
    '-bios', 'none',
    '-kernel', s3k_elf.full_path(),
    '-nographic',
    '-m', '1G',
    '-icount', '1',
    '-device', 'loader,addr=0x90000000,cpu-num=0',
    '-device', 'loader,addr=0x90000000,cpu-num=1',
]

qemu_dbg_opts = [
    '-gdb', 'tcp::3333',
    '-S',
]

subdir('tutorial.01.hello-world')
subdir('tutorial.02.trap-handler')
# subdir('tutorial.03.mem-cap')
subdir('tutorial.04.timing-cap')
subdir('tutorial.05.rpc')

alias_target('tuts',
	tut1,
    tut2,
    tut4,
    tut5,
)
