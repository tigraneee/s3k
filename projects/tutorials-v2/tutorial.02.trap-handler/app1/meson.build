linker_script = meson.current_source_dir() / 'app1.ld'

tut2_app1_elf = executable(
	'app1.elf',
	sources: files(
		'main.c',
	),
	link_args: [
		'-T', linker_script,
	],
    dependencies: [platform_dep, common_dep],
)
