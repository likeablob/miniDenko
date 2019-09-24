<template>
  <div class="card">
    <header class="card-header">
      <p class="card-header-title level">
        Device Settings
        <b-button
          :loading="isApplying"
          class="has-text-primary"
          type="is-text"
          disabled
          rounded
        ></b-button>
      </p>
    </header>

    <div class="card-content">
      <b-menu-list label="Display"></b-menu-list>
      <display :is-applying.sync="isApplying"></display>

      <b-menu-list label="WiFi"></b-menu-list>
      <wifi></wifi>

      <b-menu-list label="Other"></b-menu-list>
      <other></other>
    </div>
  </div>
</template>

<script>
import Display from './Display';
import Wifi from './WiFi';
import Other from './Other';

export default {
  components: {
    Display,
    Other,
    Wifi,
  },
  data() {
    return {
      isApplying: false,
      isLoading: false,
    };
  },
};
</script>
