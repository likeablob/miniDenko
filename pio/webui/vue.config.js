const path = require('path');
const WebpackPwaManifest = require('webpack-pwa-manifest');
const zopfli = require('@gfx/zopfli');
const CompressionWebpackPlugin = require('compression-webpack-plugin');
const WebpackShellPlugin = require('webpack-shell-plugin-alt');
const isDev = process.env.NODE_ENV !== 'production';

module.exports = {
  productionSourceMap: false,
  configureWebpack: {
    optimization: {
      splitChunks: false,
    },
    output: {
      filename: '[name].js?[hash]',
    },
    plugins: [
      new WebpackPwaManifest({
        name: 'miniDenko',
        short_name: 'miniDenko',
        description: 'miniDenko WebUI',
        background_color: '#ffffff',
        crossorigin: null,
        inject: true,
        fingerprints: false,
        icons: [
          {
            src: path.resolve('src/assets/minidenko-icon_128.png'),
            sizes: [128], // multiple sizes
          },
        ],
      }),
      !isDev &&
        new CompressionWebpackPlugin({
          threshold: 0,
          minRatio: 1,
          compressionOptions: {
            numiterations: 15,
          },
          algorithm(input, compressionOptions, callback) {
            return zopfli.gzip(input, compressionOptions, callback);
          },
        }),
      !isDev &&
        new WebpackShellPlugin({
          onBuildEnd: ['./generate-c-libs.sh'],
        }),
    ].filter(v => v),
  },
  css: {
    extract: false,
  },
};
