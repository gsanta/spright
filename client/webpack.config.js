/* eslint-disable @typescript-eslint/no-var-requires */
const webpack = require('webpack');
const MiniCssExtractPlugin = require('mini-css-extract-plugin');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const path = require('path');
const fs = require('fs');
// const BundleAnalyzerPlugin = require('webpack-bundle-analyzer').BundleAnalyzerPlugin;

// TODO: no better solution?
const srcPath = (subdir) => path.join(__dirname, 'src', subdir);
const getFilesAndDirectories = (source) => fs.readdirSync(source, { withFileTypes: true }).map((dirent) => dirent.name);
let absoluteImports = {};
getFilesAndDirectories('src').forEach((fileName) => {
  const fileNameWithoutExtension = path.parse(fileName).name;
  absoluteImports[`@/${fileNameWithoutExtension}`] = srcPath(fileName);
});

module.exports = (env) => {
  return {
    entry: {
      app: './src/index.tsx',
    },
    module: {
      rules: [
        {
          test: /\.tsx?$/,
          use: 'ts-loader',
          exclude: [/node_modules/, /src\/server/],
        },
        {
          test: /\.scss$/,
          use: [MiniCssExtractPlugin.loader, 'css-loader', 'sass-loader'],
        },
        {
          test: /\.css$/,
          use: [MiniCssExtractPlugin.loader, 'css-loader'],
        },
        {
          test: /\.(png|jpg|gif|svg)$/,
          use: [
            {
              loader: 'file-loader',
              options: {},
            },
          ],
        },
        {
          test: /\.ttf$/,
          use: ['file-loader'],
        },
      ],
    },
    plugins: [
      new webpack.HotModuleReplacementPlugin({}),
      new MiniCssExtractPlugin({
        filename: '[name].css',
      }),
      new webpack.DefinePlugin({
        DEBUG: env === 'debug' ? true : false,
      }),
      // new BundleAnalyzerPlugin({
      //     analyzerPort: 8887
      // }),
      // new webpack.optimize.LimitChunkCountPlugin({
      //   maxChunks: 1,
      // }),
      new HtmlWebpackPlugin({
        template: 'index.html',
        filename: 'index.html',
        inject: false,
      }),
    ],
    resolve: {
      extensions: ['.tsx', '.ts', '.js', 'scss', '.css'],
      alias: {
        ...absoluteImports,
      },
    },
    output: {
      filename: '[name].js',
    },
    devtool: 'eval-source-map',
    mode: 'development',
    optimization: {
      usedExports: true,
    },
    context: __dirname,
    devServer: {
      static: ['../editor/Web'],
      port: 3012,
    },
  };
};
