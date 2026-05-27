linker_script = meson.current_source_dir() / 'app2.ld'

tut5_app2_elf = executable(
	'app2.elf',
	sources: files(
		'main.c',
	),
	link_args: [
		'-T', linker_script,
	],
    dependencies: [platform_dep, common_dep],
)
