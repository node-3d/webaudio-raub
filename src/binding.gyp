{
	'variables': {
		'bin': '<!(node -p "require(\'addon-tools-raub\').getBin()")',
		'ls_include': '<!(node -p "require(\'deps-labsound-raub\').include")',
		'ls_bin': '<!(node -p "require(\'deps-labsound-raub\').bin")',
	},
	'targets': [{
		'target_name': 'webaudio',
		'includes': ['../node_modules/addon-tools-raub/utils/common.gypi'],
		'sources': [
			'cpp/bindings.cpp',
		],
		'include_dirs': [
			'<(ls_include)',
			'<!@(node -p "require(\'addon-tools-raub\').getInclude()")',
		],
		'library_dirs': ['<(ls_bin)'],
		'conditions': [
			['OS=="linux"', {
				'cflags_cc!': ['-fno-rtti', '-fno-exceptions'],
				'cflags_cc': ['-w', '-frtti', '-fexceptions'],
				'libraries': [
					"-Wl,-rpath,'$$ORIGIN'",
					"-Wl,-rpath,'$$ORIGIN/../node_modules/deps-labsound-raub/<(bin)'",
					"-Wl,-rpath,'$$ORIGIN/../../deps-labsound-raub/<(bin)'",
					'-lLabSound', '-llibnyquist', '-lasound',
				],
			}],
			['OS=="mac"', {
				'cflags_cc!': ['-fno-rtti', '-fno-exceptions'],
				'cflags_cc': ['-w', '-frtti', '-fexceptions'],
				'libraries': [
					'-Wl,-rpath,@loader_path',
					'-Wl,-rpath,@loader_path/../node_modules/deps-labsound-raub/<(bin)',
					'-Wl,-rpath,@loader_path/../../deps-labsound-raub/<(bin)',
					'-llibnyquist',
					'-L<(ls_bin)',
					'<(ls_bin)/LabSound',
				],
				'xcode_settings': {
					'DYLIB_INSTALL_NAME_BASE': '@rpath',
					'GCC_ENABLE_CPP_RTTI': 'YES',
					'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
					'OTHER_LDFLAGS': [
						'-framework AudioUnit',
						'-framework CoreAudio',
						'-framework AudioToolbox',
					],
					'OTHER_CPLUSPLUSFLAGS!': ['-fno-rtti', '-fno-exceptions']
					'OTHER_CPLUSPLUSFLAGS': ['-w', '-frtti', '-fexceptions']
				},
			}],
			['OS=="win"', {
				'libraries': [
					'-lwinmm', '-luser32', '-lLabSound', '-llibnyquist',
				],
				'defines!': ['_HAS_EXCEPTIONS=0'],
				'msvs_settings': {
					'VCCLCompilerTool': {
						'ExceptionHandling': '1',
						'AdditionalOptions!': ['/EHa-s-c-', '/GR-'],
						'AdditionalOptions': ['/EHsc', '/GR'],
					},
				},
			}],
		],
	}]
}
