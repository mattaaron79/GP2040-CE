import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";
import path from "path";

// import dev host for wsl2
const host = process.env.VITE_DEV_HOST || 'localhost';

// https://vitejs.dev/config/
export default defineConfig({
	build: {
		outDir: path.join(__dirname, "build"),
		sourcemap: false,
	},
	server: {
		host: host,
		open: true,
		port: 3000,
	},
	plugins: [react()],
	resolve: {
		alias: {
			"~bootstrap": path.resolve(__dirname, "node_modules/bootstrap"),
			lodash: 'lodash-es',
			"@proto": path.resolve(__dirname, "src_gen"),
		},
	},
});
// export default defineConfig({
//     build: {
//         outDir: path.join(__dirname, "build"),
//         sourcemap: false,
//     },
//     server: {
//         host: host,
//         open: true,
//         port: 3000,
// 		proxy: {
// 			'/api': {
// 				target: 'http://192.168.7.1',
// 				changeOrigin: true,
// 				secure: false,
// 				configure: (proxy, _options) => {
// 					proxy.on('error', (err, _req, _res) => {
// 						console.log('proxy error', err);
// 					});
// 					proxy.on('proxyReq', (proxyReq, req, _res) => {
// 						// Some embedded servers look for specific headers
// 						proxyReq.setHeader('Host', '192.168.7.1');
// 					});
// 				},
// 			},
// 		},
//     },
//     plugins: [react()],
//     resolve: {
//         alias: {
//             "~bootstrap": path.resolve(__dirname, "node_modules/bootstrap"),
//             lodash: 'lodash-es',
//             "@proto": path.resolve(__dirname, "src_gen"),
//         },
//     },
// });
