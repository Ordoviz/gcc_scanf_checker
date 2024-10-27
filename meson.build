project('scanf_checker','cpp',
	version: '0.1',
	default_options: ['buildtype=release', 'warning_level=2', 'cpp_std=gnu++17']
)

name = meson.project_name()
cc = meson.get_compiler('cpp')
gccplugins_dir = run_command('/usr/bin/gcc', '-print-file-name=plugin', check: true).stdout().strip()

foreach arg : ['-D_FORTIFY_SOURCE=3', '-Wconversion', '-Wformat=2', '-Wformat-overflow=2', '-Wformat-truncation=2', '-Wformat-signedness', '-Wuninitialized', '-Wswitch', '-Wduplicated-cond', '-Wduplicated-branches', '-Wshadow', '-Wcast-align', '-Wcast-qual', '-Wdisabled-optimization', '-Wlogical-op', '-Wpointer-arith', '-Walloca', '-Wvla', '-Walloc-zero', '-Wfloat-equal', '-Wuse-after-free=3', '-fstack-protector-all', '-Wstack-protector', '-Wstrict-overflow=4', '-Wtrampolines', '-Wshift-overflow=2', '-Wcast-qual', '-Wstringop-overflow=4', '-Wundef', '-fstack-protector-all', '-fstrict-flex-arrays=3', '-Wflex-array-member-not-at-end', '-Wuseless-cast']
	if (cc.has_argument(arg))
		add_project_arguments(arg, language: 'cpp')
	endif
endforeach

add_project_arguments(
	[
		'-isystem' + gccplugins_dir + '/include',
		'-fPIC',
		'-fno-rtti',
	],
	language: 'cpp'
)

executable(
	'scanf_checker.so',
	files('scanf_checker.cpp'),
	install: true,
	install_dir: meson.current_build_dir(),
	override_options: 'b_lundef=false',
	link_args: ['-shared'],
)
