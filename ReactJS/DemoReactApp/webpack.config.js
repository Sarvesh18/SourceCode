var path = require('path');
var webpack = require('webpack');
var nodeExternals = require('webpack-node-externals');
var HtmlWebpackPlugin = require("html-webpack-plugin");
//var MiniCssExtractPlugin = require("mini-css-extract-plugin");

var browserConfig = {
  mode: 'development',
  entry: './src/index.js',
  //externals: [nodeExternals()],
  output: {
    path: path.resolve(__dirname, 'dist'),
    filename: 'bundle.js',
    publicPath: '/'
  }, 
  devServer: {
    host: "localhost",
    inline: true,
    //open: true,
    //hot: true,
    historyApiFallback: true,
    port: 8090
  },
  module: {
    rules: [
      {  
        test: /\.(jsx|js)$/,
        exclude: /node_modules/,
        use: 'babel-loader' 
      },
      {
        test: /\.css$/,
        loader: ['style-loader','css-loader']
        //'style-loader!css-loader?modules=true&localIdentName=[name]__[local]___[hash:base64:5]'
      },
      /*
      {
        test: /\.()$/,
        loader: 'file-loader', 
      },
      */ 
      {
        test: /\.(svg|png)$/, 
        loader: 'url-loader'
      }
     
    ]
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: "./src/static/index.html",
      filename: "index.html"
    }),
    new webpack.DefinePlugin({
      __isBrowser__: "true"
    })
  ]
}
/*
var serverConfig = {
  mode: 'development',
  entry: './src/server/server.js',
  target: 'node',
  externals: [nodeExternals()],
  output: {
    path: path.resolve(__dirname, 'dist'),
    filename: 'server.js',
    //publicPath: '/'
  },
  module: {
    rules: [
      { 
        test: /\.(jsx|js)$/, 
        use: 'babel-loader' 
      },
      {
        test: /\.css$/,
        use: [
          {
            loader: MiniCssExtractPlugin.loader,
          },
          "css-loader"
        ]
      },
      {
        test: /\.(svg)$/, 
        loader: 'url-loader'
      }
    ]
  },
  plugins: [
    new MiniCssExtractPlugin({
      filename: "style.css",
      chunkFilename: "[id].css"
    }),
    new webpack.DefinePlugin({
      __isBrowser__: "false"
    })
  ]
}
*/
//module.exports = [browserConfig, serverConfig]
module.exports = [browserConfig]