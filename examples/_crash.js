'use strict';

var SegfaultHandler = require('segfault-handler');
 
SegfaultHandler.registerHandler('crash.log');

const { AudioContext } = require('..');

const read = require('./utils/read');


(async () => { try {
	
	const objects = [];
	const scene = [];
	
	const context = new AudioContext();
	
	const clip = await read(`${__dirname}/samples/hit.wav`);
	
	const gain = context.createGain();
	const gain.connect( context.destination );
	
	const buffer = await new Promise(res => context.decodeAudioData(clip, b => res(b)));
	
	// Create objects when audio buffer is loaded
	for (let i = 0; i < count; i++) {
		const s = i / count * Math.PI * 2;
		const ball = new three.Mesh( ballGeometry, ballMaterial );
		ball.castShadow = true;
		ball.userData.down = false;
		ball.position.x = radius * Math.cos( s );
		ball.position.z = radius * Math.sin( s );
		const audio = new three.PositionalAudio( listener );
		audio.setBuffer( buffer );
		audio._buf = buffer;
		ball.add( audio );
		scene.add( ball );
		objects.push( ball );
	}
	
	const renderer = new three.WebGLRenderer( { antialias: true } );
	renderer.shadowMap.enabled = true;
	renderer.setSize( window.innerWidth, window.innerHeight );
	renderer.setClearColor( 0x000000 );
	renderer.setPixelRatio( window.devicePixelRatio );
	
	//
	// const controls = new three.OrbitControls( camera, renderer.domElement );
	// controls.minDistance = 1;
	// controls.maxDistance = 25;
	//
	
	window.addEventListener( 'resize', () => {
		camera.aspect = window.innerWidth / window.innerHeight;
		camera.updateProjectionMatrix();
		renderer.setSize( window.innerWidth, window.innerHeight );
	});
	
	const speed = 0.002;
	const height = 3;
	const offset = 0.5;
	
	const render = () => {
		const time = Date.now();
		for ( let i = 0; i < objects.length; i++ ) {
			const ball = objects[ i ];
			const previousHeight = ball.position.y;
			const al = i * offset + ( time * speed );
			
			ball.position.y = Math.abs( Math.sin( al ) * height );
			
			if (ball.position.y === previousHeight) {
				continue;
			}
			
			if ( ball.position.y < previousHeight ) {
				ball.userData.down = true;
			} else {
				// If ball changed direction from down to up
				if ( ball.userData.down === true ) {
					
					const audio = ball.children[ 0 ];
					
					// play audio with perfect timing when ball hits the surface
					audio.play();
					
					ball.userData.down = false;
					
				}
			}
		}
		renderer.render( scene, camera );
	};
	
	const animate = () => {
		requestAnimationFrame( animate );
		render();
	};
	
	animate();
	
} catch (e) { console.error(e); } })();
