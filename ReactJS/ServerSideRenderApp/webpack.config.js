var path = require('path');
var webpack = require('webpack');
var nodeExternals = require('webpack-node-externals');
//var ExtractTextPlugin = require("extract-text-webpack-plugin");
var HtmlWebpackPlugin = require("html-webpack-plugin");
var MiniCssExtractPlugin = require("mini-css-extract-plugin");



var browserConfig = {
  mode: 'development',
  entry: './src/client.js',
  output: {
    path: path.resolve(__dirname, 'dist'),
    filename: 'bundle.js',
    //publicPath: '/'
  },
  module: {
    rules: [
      { 
        //test: /\.(js)$/, 
        test: /\.(jsx|js)$/,
        exclude: /node_modules/,
        use: 'babel-loader' 
      },
      {
        test: /\.(jsx|js)$/,
        exclude: /node_modules/,
        use: ['babel-loader','eslint-loader']
      },
      {
        test: /\.css$/,
        loader: 'style-loader!css-loader?modules=true&localIdentName=[name]__[local]___[hash:base64:5]'
      }, 
      {
        test: /\.gif$/, 
        loader: 'url-loader'
      },
      {
        test: /\.(ttf|eot|svg)$/,
        loader: 'file-loader', 
      }
    ]
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: "./src/index.html",
      filename: "index.html"
    }),
    new webpack.DefinePlugin({
      __isBrowser__: "true"
    })
  ]
}

var serverConfig = {
  mode: 'development',
  entry: './src/server.js',
  target: 'node',
  externals: [nodeExternals()],
  output: {
    path: path.resolve(__dirname, 'dist'),
    filename: 'server.js',
    //publicPath: '/'
  },/*
  devServer: {
    host: "localhost",
    inline: true,
    open: true,
    hot: true,
    port: 8080
  }*/
  module: {
    rules: [
      { 
        //test: /\.(js)$/,
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
      }
      /*
      {
        test: /\.css$/,
        //loader: 'style-loader!css-loader?modules=true&localIdentName=[name]__[local]___[hash:base64:5]'
        loader: ExtractTextPlugin.extract({ 
          fallback: "style-loader", 
          use: "css-loader?modules=true&localIdentName=[name]__[local]___[hash:base64:5]" 
        }) 
      },
      */
    ]
  },
  plugins: [
    new MiniCssExtractPlugin({
      filename: "style.css",
      chunkFilename: "[id].css"
    }),
    /*new ExtractTextPlugin({
      filename: "style.css",
      allChunks: true
    })
    */
    new webpack.DefinePlugin({
      __isBrowser__: "false"
    })
  ]
}

module.exports = [browserConfig, serverConfig]