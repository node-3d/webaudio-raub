{
	'variables': {
		'bin': '<!(node -p "require(\'addon-tools-raub\').getBin()")',
		'ls_include': '<!(node -p "require(\'deps-labsound-raub\').include")',
		'ls_bin': '<!(node -p "require(\'deps-labsound-raub\').bin")',
	},
	'targets': [{
		'target_name': 'webaudio',
		'sources': [
			'cpp/bindings.cpp',
			'cpp/common.cpp',
			'cpp/analyser-node.cpp',
			'cpp/audio-buffer.cpp',
			'cpp/audio-buffer-source-node.cpp',
			'cpp/audio-context.cpp',
			'cpp/audio-destination-node.cpp',
			'cpp/audio-listener.cpp',
			'cpp/audio-node.cpp',
			'cpp/audio-param.cpp',
			'cpp/audio-setting.cpp',
			## 'cpp/audio-processing-event.cpp',
			'cpp/audio-scheduled-source-node.cpp',
			'cpp/base-audio-context.cpp',
			'cpp/biquad-filter-node.cpp',
			## 'cpp/channel-merger-node.cpp',
			## 'cpp/channel-splitter-node.cpp',
			## 'cpp/constant-source-node.cpp',
			'cpp/convolver-node.cpp',
			'cpp/delay-node.cpp',
			## 'cpp/dynamics-compressor-node.cpp',
			'cpp/gain-node.cpp',
			## 'cpp/iir-filter-node.cpp',
			## 'cpp/media-element-audio-source-node.cpp',
			## 'cpp/media-stream-audio-destination-node.cpp',
			## 'cpp/media-stream-audio-source-node.cpp',
			## 'cpp/offline-audio-completion-event.cpp',
			## 'cpp/offline-audio-context.cpp',
			'cpp/oscillator-node.cpp',
			'cpp/panner-node.cpp',
			## 'cpp/periodic-wave.cpp',
			## 'cpp/script-processor-node.cpp',
			## 'cpp/stereo-panner-node.cpp',
			## 'cpp/wave-shaper-node.cpp',
		],
		'defines': ['UNICODE', '_UNICODE'],
		'include_dirs': [
			'<(ls_include)',
			'<!@(node -p "require(\'addon-tools-raub\').getInclude()")',
		],
		'cflags_cc': ['-std=c++17', '-fno-exceptions'],
		'cflags': ['-fno-exceptions'],
		'library_dirs': ['<(ls_bin)'],
		'conditions': [
			['OS=="linux"', {
				'cflags_cc': ['-w'],
				'libraries': [
					"-Wl,-rpath,'$$ORIGIN'",
					"-Wl,-rpath,'$$ORIGIN/../node_modules/deps-labsound-raub/<(bin)'",
					"-Wl,-rpath,'$$ORIGIN/../../deps-labsound-raub/<(bin)'",
					'-lLabSound', '-llibnyquist', '-lsamplerate', '-lasound',
				],
				'defines': ['__linux__'],
			}],
			['OS=="mac"', {
				'cflags_cc': ['-w'],
				'libraries': [
					'-Wl,-rpath,@loader_path',
					'-Wl,-rpath,@loader_path/../node_modules/deps-labsound-raub/<(bin)',
					'-Wl,-rpath,@loader_path/../../deps-labsound-raub/<(bin)',
					'-llibnyquist', '-lsamplerate',
					'-L<(ls_bin)',
					'<(ls_bin)/LabSound',
				],
				'xcode_settings': {
					'DYLIB_INSTALL_NAME_BASE': '@rpath',
					'OTHER_LDFLAGS': [
						'-framework AudioUnit',
						'-framework CoreAudio',
						'-framework AudioToolbox',
					],
				},
				'MACOSX_DEPLOYMENT_TARGET': '10.9',
				'defines': ['__APPLE__'],
				'CLANG_CXX_LIBRARY': 'libc++',
				'OTHER_CFLAGS': ['-std=c++17', '-fno-exceptions'],
			}],
			['OS=="win"', {
				'libraries': [
					'-lwinmm', '-luser32',
					'-lLabSound', '-llibnyquist', '-lsamplerate'
				],
				'defines': ['WIN32_LEAN_AND_MEAN', 'VC_EXTRALEAN', '_WIN32', '_HAS_EXCEPTIONS=0'],
				'msvs_settings' : {
					'VCCLCompilerTool' : {
						'AdditionalOptions' : [
							'/O2','/Oy','/GL','/GF','/Gm-', '/std:c++17',
							'/EHa-s-c-','/MT','/GS','/Gy','/GR-','/Gd',
						]
					},
					'VCLinkerTool' : {
						'AdditionalOptions' : ['/DEBUG:NONE', '/LTCG', '/OPT:NOREF'],
					},
				},
			}],
		],
	}]
}
