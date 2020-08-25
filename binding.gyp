{
	'targets': [
		{
			'target_name': 'pipe',
			'sources': ['src/pipe.cpp'],
			'include_dirs': ["<!@(node --no-warnings -p \"require('node-addon-api').include\")"],
			'dependencies': ["<!(node --no-warnings -p \"require('node-addon-api').gyp\")"],
			'conditions': [
				['OS=="mac"', {
					'cflags+': ['-fvisibility=hidden'],
					'xcode_settings': {
					  'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES', # -fvisibility=hidden
					}
				}]
			],
		 	'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
		}
	]
}
