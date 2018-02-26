{
	'variables': {
		'rm'             : '<!(node -e "require(\'addon-tools-raub\').rm()")',
		'cp'             : '<!(node -e "require(\'addon-tools-raub\').cp()")',
		'mkdir'          : '<!(node -e "require(\'addon-tools-raub\').mkdir()")',
		'bullet_include' : '<!(node -e "require(\'deps-bullet-raub\').include()")',
		'bullet_bin'     : '<!(node -e "require(\'deps-bullet-raub\').bin()")',
	},
	'targets': [
		{
			'target_name': 'bullet',
			'sources': [
				'cpp/bindings.cpp',
				'cpp/body.cpp',
				'cpp/joint.cpp',
				'cpp/scene.cpp',
				'cpp/trace.cpp',
			],
			'include_dirs': [
				'<!@(node -e "require(\'addon-tools-raub\').include()")',
				'<(bullet_include)',
			],
			'library_dirs': [ '<(bullet_bin)' ],
			'libraries'    : [ '-lbullet' ],
			'conditions'   : [
				[
					'OS=="linux"', {
						'libraries': [
							'-Wl,-rpath,<(bullet_bin)',
						],
					}
				],
				[
					'OS=="mac"', {
						'libraries': [
							'-Wl,-rpath,<(bullet_bin)',
						],
					}
				],
				[
					'OS=="win"',
					{
						'msvs_settings' : {
							'VCCLCompilerTool' : {
								'AdditionalOptions' : [
									'/O2','/Oy','/GL','/GF','/Gm-', '/Fm-',
									'/EHsc','/MT','/GS','/Gy','/GR-','/Gd',
								]
							},
							'VCLinkerTool' : {
								'AdditionalOptions' : ['/RELEASE','/OPT:REF','/OPT:ICF','/LTCG']
							},
						},
					},
				],
			],
		},
		{
			'target_name'  : 'make_directory',
			'type'         : 'none',
			'dependencies' : ['bullet'],
			'actions'      : [{
				'action_name' : 'Directory created.',
				'inputs'      : [],
				'outputs'     : ['build'],
				'action': ['<(mkdir)', '-p', 'binary']
			}],
		},
		{
			'target_name'  : 'copy_binary',
			'type'         : 'none',
			'dependencies' : ['make_directory'],
			'actions'      : [{
				'action_name' : 'Module copied.',
				'inputs'      : [],
				'outputs'     : ['binary'],
				'action'      : ['<(cp)', 'build/Release/bullet.node', 'binary/bullet.node'],
			}],
		},
		{
			'target_name'  : 'remove_extras',
			'type'         : 'none',
			'dependencies' : ['copy_binary'],
			'actions'      : [{
				'action_name' : 'Build intermediates removed.',
				'inputs'      : [],
				'outputs'     : ['cpp'],
				'conditions'  : [
					[ 'OS=="linux"', { 'action' : [
						'rm',
						'<(module_root_dir)/build/Release/obj.target/bullet/cpp/bullet.o',
						'<(module_root_dir)/build/Release/obj.target/bullet.node',
						'<(module_root_dir)/build/Release/bullet.node'
					] } ],
					[ 'OS=="mac"', { 'action' : [
						'rm',
						'<(module_root_dir)/build/Release/obj.target/bullet/cpp/bindings.o',
						'<(module_root_dir)/build/Release/obj.target/bullet/cpp/body.o',
						'<(module_root_dir)/build/Release/obj.target/bullet/cpp/joint.o',
						'<(module_root_dir)/build/Release/obj.target/bullet/cpp/scene.o',
						'<(module_root_dir)/build/Release/obj.target/bullet/cpp/trace.o',
						'<(module_root_dir)/build/Release/bullet.node'
					] } ],
					[ 'OS=="win"', { 'action' : [
						'<(rm)',
						'<(module_root_dir)/build/Release/glfw.*',
						'<(module_root_dir)/build/Release/obj/glfw/*.*'
					] } ],
				],
			}],
		},
	]
}
