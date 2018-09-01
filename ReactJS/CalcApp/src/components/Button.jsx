import React, { Component } from 'react';
import './style.css';

import {connect} from 'react-redux';
import {bindActionCreators} from 'redux';
import {add,sub,mul,div,concat,equal} from '../actions';

class Button extends Component {
  componentDidMount() {
    console.log('componentDidMount Button');
    //for(let i=2;i<18;i++){
       //document.getElementById('grid').innerHTML += `<div onClick='${}' className="item${i+1} grid-item">${this.props.value[i]}</div>`;
    //}
  }
  calc(ch) {
    console.log('calc',ch);
    if(ch==='+'){
      this.props.add(ch);
    }
    else if(ch==='-'){
      this.props.sub(ch);
    }
    else if(ch==='*'){
      this.props.mul(ch);
    }
    else if(ch==='/'){
      this.props.div(ch);
    }
    else {
      this.props.concat(ch);
    }
  }
  render() {
    return (
      <div id="grid" className="grid-container">
        {console.log('return Button')}
        <div onClick={()=> this.calc(this.props.value[2])} className="item3 grid-item">{this.props.value[2]}</div>
        <div onClick={()=> this.calc(this.props.value[3])} className="item4 grid-item">{this.props.value[3]}</div>
        <div onClick={()=> this.calc(this.props.value[4])} className="item5 grid-item">{this.props.value[4]}</div>
        <div onClick={()=> this.calc(this.props.value[5])} className="item6 grid-item">{this.props.value[5]}</div>
        <div onClick={()=> this.calc(this.props.value[6])} className="item7 grid-item">{this.props.value[6]}</div>
        <div onClick={()=> this.calc(this.props.value[7])} className="item8 grid-item">{this.props.value[7]}</div>
        <div onClick={()=> this.calc(this.props.value[8])} className="item9 grid-item">{this.props.value[8]}</div>
        <div onClick={()=> this.calc(this.props.value[9])} className="item10 grid-item">{this.props.value[9]}</div>
        <div onClick={()=> this.calc(this.props.value[10])} className="item11 grid-item">{this.props.value[10]}</div>
        <div onClick={()=> this.calc(this.props.value[11])} className="item12 grid-item">{this.props.value[11]}</div>
        <div onClick={()=> this.calc(this.props.value[12])} className="item13 grid-item">{this.props.value[12]}</div>
        <div onClick={()=> this.calc(this.props.value[13])} className="item14 grid-item">{this.props.value[13]}</div>
        <div onClick={()=> this.calc(this.props.value[14])} className="item15 grid-item">{this.props.value[14]}</div>
        <div onClick={()=> this.calc(this.props.value[15])} className="item16 grid-item">{this.props.value[15]}</div>
        <div onClick={()=> this.calc(this.props.value[16])} className="item17 grid-item">{this.props.value[16]}</div>
        <div onClick={()=> this.calc(this.props.value[17])} className="item18 grid-item">{this.props.value[17]}</div>
      </div>
    );
  }
}
function mapStateToProps(state) {
    console.log('mapStateToProps Button',state);
    return {value:state};
}

function mapDispatchToProps(dispatch) {
  // console.log('mapDispatchToProps Display',dispatch);
  return bindActionCreators({add,sub,mul,div,concat,equal},dispatch);
}

export default connect(mapStateToProps,mapDispatchToProps)(Button);
