import React, { Component } from 'react';
import './style.css';

import {connect} from 'react-redux';
import {bindActionCreators} from 'redux';
import {add,sub,mul,div,concat,equal} from '../actions';

class Display extends Component {
  componentDidMount() {
    console.log('componentDidMount Display');
  }
  render() {
    console.log('Display:',this);

    return (
      <div className="grid-container">
        {console.log('return Display',this.props)}
        <div className="item1 grid-item"> {this.props.value[0]} </div>
        <div className="item2 grid-item"> {this.props.value[1]} </div>
      </div>
    );
  }
}

function mapStateToProps(state) {
    console.log('mapStateToProps Display',state);
    return {value:state}
}

function mapDispatchToProps(dispatch) {
  //console.log('mapDispatchToProps Display',dispatch);
  return bindActionCreators({add,sub,mul,div,concat,equal},dispatch);
}

export default connect(mapStateToProps,mapDispatchToProps)(Display);
