var ResultView = function() {
  this._filter = function() { return true; };
  this._group = function(result) { return result.starts[0]};
  this._sort = function() { };
};

var ResultRange = function() {
  this.range = [ null, null ];
};

ResultRange.prototype.expand = function(val) {
  if (this.range[0] === null || val < this.range[0]) {
    this.range[0] = val;
  }
  if (this.range[1] === null || val > this.range[1]) {
    this.range[1] = val;
  }
}

var ResultViewParams = function(results, x_range, y_range) {
  this.results = results;
  this.x = x_range;
  this.y = y_range;
};

ResultView.prototype.processedResults = function(input) {
  var x_range = new ResultRange();
  var y_range = new ResultRange();

  var results = { };
  for (var i in input.results) {
    var data_set = input.results[i];
    for (var r in data_set.results) {
      var result = data_set.results[r];
      if (!this._filter(result)) {
        continue;
      }

      var grp = this._group(result);

      if (results.hasOwnProperty(grp)) {
        results[grp] = Result.combine(results[grp], result);
      }
      else {
        results[grp] = Result.clone(result);
      }
      
      for (var i in result.starts) {
        x_range.expand(result.starts[i]);
      }
    }
  }

  var result_list = [];
  for (var key in results) {
    result_list.push(results[key]);
  }

  this._sort(result_list);

  y_range.expand(0);
  y_range.expand(50);

  return new ResultViewParams(result_list, x_range, y_range);
}
