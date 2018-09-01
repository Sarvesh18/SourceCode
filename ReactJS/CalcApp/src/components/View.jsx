import React, { Component } from 'react';
import './style.css';

import {style,fixed} from './style';

import Display from './Display';
import Button from './Button';
import Controller from './Controller';

const Test = () => {
    return (
    <div style={style.col}>Test</div>
    );
};

class View extends Component {
  componentDidMount() {
    console.log('componentDidMount View');
  }
  createMarkup() {
    let div='';
    for(let i=0;i<5;i++)
    {
      div =div + `<div>${i}</div>`;
    }
    return {__html: div};
  }
  MyComponent() {
    return <div dangerouslySetInnerHTML={this.createMarkup()} />;
  }
  render() {
    return (
      <div className="main">
        {this.MyComponent()}
        <Test />
        {console.log('return View')}
        <div className="container">
          <div style={{...style.bg, ...style.size}}>
            Sarvesh
          </div>
          <div style={{marginTop: 20,marginBottom: 20}}>
            Singh
          </div>
          <Display />
          <Button />
          <Controller />
        </div>
      </div>
    );
  }
}

export default View;
