// this is how we will require our module
const m = require('./');
const _ = new m.Underscore();
const newValue = _.map([true, 1, 'string', [ 'array'], {'hello' : 'object' }, undefined], (item) => {
  return item;
} );

console.log(newValue);

// const newValue1 = [true, 1, 'string', [ 'array'], {'hello' : 'object' }, undefined]. map((item) => {
//   console.log(newValue1);
//   return item;
// });

console.log(newValue1);

